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
    ${convertType(
      func.ret
    )} ret = Runtime::Instance().GetOMPAPI()->${group}.${name}(${func.params
        .map((arg) => `${arg.name}`)
        .join(", ")});
    API_RETURN(${convertType(func.ret)} ret${
        retArgs.length ? ", " : ""
      }${retArgs
        .map((arg) => `${convertType(arg.type)} ${arg.name}`)
        .join(", ")});
}\n`
    );
  });
});
