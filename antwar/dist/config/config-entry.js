"use strict";

var _webpackMerge = require("webpack-merge");

var _webpackMerge2 = _interopRequireDefault(_webpackMerge);

var _antwarConfig = require("_antwar-config");

var _antwarConfig2 = _interopRequireDefault(_antwarConfig);

var _defaultAntwar = require("./default-antwar");

var _defaultAntwar2 = _interopRequireDefault(_defaultAntwar);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

module.exports = (0, _webpackMerge2.default)((0, _defaultAntwar2.default)(), (0, _antwarConfig2.default)(process.env.NODE_ENV));