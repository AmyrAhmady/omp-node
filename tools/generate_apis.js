const { writeFileSync, appendFileSync, mkdirSync, existsSync } = require("fs");
const apis = require("../deps/omp-capi/apidocs/api.json");
const events = require("../deps/omp-capi/apidocs/events.json");

const convertType = (type) => {
  if (type == "const char*") {
    return "StringCharPtr";
  } else if (type == "void*") {
    return "objectPtr";
  } else if (type == "CAPIStringView*") {
    return "OutputStringViewPtr";
  } else if (type == "int*") {
    return "IntRef";
  } else if (type == "bool*") {
    return "BoolRef";
  } else if (type == "float*") {
    return "FloatRef";
  } else if (type == "uint8_t*") {
    return "UInt8Ref";
  } else if (type == "uint32_t*") {
    return "UInt32Ref";
  } else {
    return type;
  }
};

const isRetArg = (type) => {
  if (type == "CAPIStringView*") {
    return true;
  } else if (type == "int*") {
    return true;
  } else if (type == "float*") {
    return true;
  } else if (type == "bool*") {
    return true;
  } else if (type == "uint8_t*") {
    return true;
  } else if (type == "uint32_t*") {
    return true;
  } else {
    return false;
  }
};

Object.entries(apis).forEach(([key, funcs]) => {
  if (key == "Component") return;
  const dir = `../src/api/${key}`;

  if (!existsSync(dir)) mkdirSync(dir);

  const filePath = dir + "/APIs.cpp";

  writeFileSync(
    filePath,
    `#include "../Impl.hpp"
#include "../MacroMagic.hpp"\n`
  );

  funcs.forEach((func) => {
    const retArgs = func.params.filter((arg) => isRetArg(arg.type));
    const group = func.name.split("_")[0];
    const name = func.name.split("_")[1];
    appendFileSync(
      filePath,
      `\nDECLARE_API(${group}, ${name}${
        func.params.length ? ", " : ""
      }${func.params
        .map((arg) => `${convertType(arg.type)} ${arg.name}`)
        .join(", ")})
{
\t${convertType(
      func.ret
    )} ret = Runtime::Instance().GetOMPAPI()->${group}.${name}(${func.params
        .map((arg) => `${arg.name}`)
        .join(", ")});
\tAPI_RETURN(${convertType(func.ret)} ret${
        retArgs.length ? ", " : ""
      }${retArgs
        .map((arg) => `${convertType(arg.type)} ${arg.name}`)
        .join(", ")});
}\n`
    );
  });
});

const filePathEvents = "../src/api/Events.cpp";
writeFileSync(
  filePathEvents,
  `#include "./Impl.hpp"

class OMP_NODE_Events
{
public:
\tOMP_NODE_Events()
\t{
`
);

Object.entries(events).forEach(([key, funcs]) => {
  // ignore onTick event generation
  if (key == "Core") return;
  funcs.forEach((func) => {
    appendFileSync(
      filePathEvents,
      `\t\tEventManager::Instance().Register("${func.name}", EventCallback_Common(&${func.name}));\n`
    );
  });
});

appendFileSync(filePathEvents, `    }\n`);

Object.entries(events).forEach(([key, funcs]) => {
  // ignore onTick event generation
  if (key == "Core") return;
  funcs.forEach((func) => {
    const no_on =
      func.name.slice(2).charAt(0).toLowerCase() + func.name.slice(3);
    appendFileSync(
      filePathEvents,
      `\n\tstatic bool ${func.name}(EventArgs_${func.name}* args)\n\t{\n`
    );

    appendFileSync(
      filePathEvents,
      `\t\treturn Runtime::Instance().DispatchEvents("${no_on}", true, EventBadRet::${
        func.badret.charAt(0).toUpperCase() + func.badret.slice(1)
      }, ${func.args
        .map(
          (arg) =>
            `${arg.type == "void*" ? "uintptr_t(" : ""}*(args->list->${
              arg.name
            })${arg.type == "void*" ? ")" : ""}`
        )
        .join(", ")});\n`
    );

    appendFileSync(filePathEvents, `\t}\n`);
  });
});

appendFileSync(
  filePathEvents,
  `};\n\nOMP_NODE_Events OMP_NODE_Events_instance;\n`
);
