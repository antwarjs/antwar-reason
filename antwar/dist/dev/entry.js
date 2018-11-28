"use strict";

var _react = require("react");

var _react2 = _interopRequireDefault(_react);

var _reactDom = require("react-dom");

var _reactDom2 = _interopRequireDefault(_reactDom);

var _reactRouterDom = require("react-router-dom");

var _antwarConfig = require("antwar-config");

var _antwarConfig2 = _interopRequireDefault(_antwarConfig);

var _paths = require("../paths");

var _paths2 = _interopRequireDefault(_paths);

var _BodyContent = require("../BodyContent");

var _BodyContent2 = _interopRequireDefault(_BodyContent);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

const container = document.createElement("div");
document.body.appendChild(container);

_reactDom2.default.render(_react2.default.createElement(
  _reactRouterDom.BrowserRouter,
  null,
  _react2.default.createElement(_reactRouterDom.Route, {
    component: ({ location }) => {
      const allPages = _paths2.default.getAllPages(_antwarConfig2.default);
      const page = _paths2.default.getPageForPath(location.pathname, allPages);

      return (0, _BodyContent2.default)(page, allPages)({ location });
    }
  })
), container);