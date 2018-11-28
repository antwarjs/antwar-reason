"use strict";

var _path = require("path");

var path = _interopRequireWildcard(_path);

var _webpackMerge = require("webpack-merge");

var _webpackMerge2 = _interopRequireDefault(_webpackMerge);

var _miniHtmlWebpackPlugin = require("mini-html-webpack-plugin");

var _miniHtmlWebpackPlugin2 = _interopRequireDefault(_miniHtmlWebpackPlugin);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

module.exports = config => {
  const devConfig = {
    mode: "development",
    node: { __filename: true, fs: "empty" },
    output: {
      path: path.join(process.cwd(), "./.antwar/build/"),
      filename: "[name].js",
      publicPath: "/",
      chunkFilename: "[chunkhash].js"
    },
    plugins: [new _miniHtmlWebpackPlugin2.default()]
  };

  return (0, _webpackMerge2.default)(devConfig, config.webpack);
};