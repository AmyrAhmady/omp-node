#pragma once

const Impl::String bootstrap = R"(
// clang-format off
const { esmLoader } = require("internal/process/esm_loader");
const path = require("path");
const dns = require('dns');
const url = require("url");
const util = require("util");
const EventEmitter = require('events');

// const inspector = require("inspector");

__internal_omp.eventEmitter_raw = new EventEmitter();
__internal_omp.eventEmitter = new EventEmitter();

async function __internal_globalEventHandler(name, badRet, ...args)
{
  const listeners = __internal_omp.eventEmitter_raw.listeners(name);
  let result = true;
  for await (const listener of listeners) {
    result = await listener(badRet, ...args);
    if (typeof result === "boolean" || typeof result === "number") {
      switch (badRet) {
        case 1:
          if (!result) {
            return false;
          }
          break;
        case 2:
          if (result) {
            return true;
          }
          break;
        case 0:
        default:
          break;
      }
    }
  }

  return result;
}

// Set native logger function
__internal_omp.log = (...args) => {
  __internal_ompLogBridge(util.format(...args));
}

function addListener(name, callback) {
  if (callback && name.length) {
    __internal_omp.eventEmitter.addListener(name, callback);
  }
}

function removeListener(name, callback) {
  if (callback && name.length) {
    __internal_omp.eventEmitter.removeListener(name, callback);
  }
}

function removeAllListeners(name, callback) {
  if (callback && name.length) {
    __internal_omp.eventEmitter.removeAllListeners(name);
  }
}

__omp = {
  ...__omp,
  resource: __internal_resource,
  log: __internal_omp.log,
  on: addListener,
  addListener: addListener,
  removeListener: removeListener,
  removeAllListeners: removeAllListeners
};

(async () => {
  const resource = __internal_resource;

  process.on("uncaughtException", (err) => {
    console.log(`Uncaught exception: ${err.stack ? `${err.stack}` : `${err.message}`}`);
  });

  // Allows users to use "localhost" address instead of 127.0.0.1 for tcp connections (e.g. database)
  // https://github.com/nodejs/node/issues/40702#issuecomment-958157082
  dns.setDefaultResultOrder('ipv4first');

  startError = false;
  try {
    const config = __internal_inspectorConfig;
    if (config.enabled) {
      const host = config.host ?? "127.0.0.1";
      const port = config.port ?? 9229;
      const wait = config.wait ?? false;

      inspector.open(port, host, wait);
    }

    // Get the path to the main file for this resource, and load it
    const _path = path.resolve(resource.path, resource.entryFile);
    await esmLoader.import(url.pathToFileURL(_path).toString(), "", {});

  } catch (e) {
    console.error(e);
    startError = true;
  }

  __internal_setEventHandlerFunction(__internal_globalEventHandler)
  __internal_resourceLoaded(resource.name, startError);
})();
)";
