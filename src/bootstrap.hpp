#pragma once

const Impl::String bootstrap = R"(
// clang-format off
const { esmLoader } = require("internal/process/esm_loader");
const path = require("path");
const dns = require('dns');
const url = require("url");
const util = require("util");
// const inspector = require("inspector");

__internal_omp.log = (...args) => {
    __internal_ompLogBridge(util.format(...args));
}

(async () => {
  const resource = __internal_resource;

  process.on("uncaughtException", (err) => {
    console.log(`Uncaught exception: ${err.stack ? `${err.stack}` : `${err.message}`}`);
  });

  // Allows users to use "localhost" address instead of 127.0.0.1 for tcp connections (e.g. database)
  // https://github.com/nodejs/node/issues/40702#issuecomment-958157082
  dns.setDefaultResultOrder('ipv4first');

  try {
    // const config = __internal_resource_config;
    // if (config.inspector) {
    //   const host = config.inspector.host ?? '127.0.0.1';
    //   const port = config.inspector.port ?? 9229;
    //   const wait = config.inspector.wait ?? false;

    //   inspector.open(port, host, wait);
    // }

    // Get the path to the main file for this resource, and load it
    const _path = path.resolve(resource.path, resource.entryFile);
    await esmLoader.import(url.pathToFileURL(_path).toString(), "", {});

  } catch (e) {
    console.error(e);
  }

  __internal_resourceLoaded(resource.name);
})();
)";
