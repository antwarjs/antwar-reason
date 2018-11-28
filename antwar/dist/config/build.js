"use strict";

var _path = require("path");

var path = _interopRequireWildcard(_path);

var _webpackMerge = require("webpack-merge");

var _webpackMerge2 = _interopRequireDefault(_webpackMerge);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

module.exports = function ({ configurations }) {
  const buildConfig = {
    mode: "production",
    node: {
      fs: "empty"
    },
    name: "server",
    target: "node",
    entry: {
      site: path.join(__dirname, "../build/site.js")
    },
    output: {
      path: path.join(process.cwd(), configurations.antwar.output),
      filename: "[name].js",
      publicPath: "/",
      libraryTarget: "commonjs2"
    }
  };

  return (0, _webpackMerge2.default)(buildConfig, configurations.webpack);
};