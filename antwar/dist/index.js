"use strict";

var _path = require("path");

var path = _interopRequireWildcard(_path);

var _rimraf = require("rimraf");

var _rimraf2 = _interopRequireDefault(_rimraf);

var _webpackMerge = require("webpack-merge");

var _webpackMerge2 = _interopRequireDefault(_webpackMerge);

var _defaultAntwar = require("./config/default-antwar");

var _defaultAntwar2 = _interopRequireDefault(_defaultAntwar);

var _defaultWebpack = require("./config/default-webpack");

var _defaultWebpack2 = _interopRequireDefault(_defaultWebpack);

var _deepmerge = require("deepmerge");

var _deepmerge2 = _interopRequireDefault(_deepmerge);

var _build = require("./build");

var _build2 = _interopRequireDefault(_build);

var _dev = require("./dev");

var _dev2 = _interopRequireDefault(_dev);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

exports.develop = execute(develop);
exports.start = exports.develop; // convenience alias
exports.build = execute(_build2.default);

function execute(target) {
  return ({ configurationPaths, environment }) => {
    process.env.NODE_ENV = environment;

    return target({
      environment,
      configurationPaths,
      configurations: {
        antwar: (0, _deepmerge2.default)((0, _defaultAntwar2.default)(), require(configurationPaths.antwar)(environment)),
        webpack: (0, _webpackMerge2.default)((0, _defaultWebpack2.default)({ configurationPaths }), require(configurationPaths.webpack)(environment))
      }
    });
  };
}

function develop({ configurations }) {
  const cwd = process.cwd();
  const buildDir = path.join(cwd, "./.antwar");

  return new Promise((resolve, reject) => {
    (0, _rimraf2.default)(buildDir, err => {
      if (err) {
        return reject(err);
      }

      return _build2.default.devIndex({ configurations }).then(_dev2.default.server.bind(null, configurations)).then(resolve).catch(reject);
    });
  });
}