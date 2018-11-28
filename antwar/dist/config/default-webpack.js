"use strict";

var _path = require("path");

var path = _interopRequireWildcard(_path);

var _webpack = require("webpack");

var _webpack2 = _interopRequireDefault(_webpack);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

module.exports = function ({ configurationPaths }) {
  const cwd = process.cwd();

  return {
    resolve: {
      alias: {
        "_antwar-config": configurationPaths.antwar,
        "antwar-config": path.join(__dirname, "config-entry.js") // global access to antwar config
      },
      modules: [path.join(cwd, "node_modules"), "node_modules"]
    },
    resolveLoader: {
      modules: [cwd, path.join(__dirname, "..", "node_modules"), "node_modules"]
    }
  };
};