"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _react = require("react");

var _react2 = _interopRequireDefault(_react);

var _antwarConfig = require("antwar-config");

var _antwarConfig2 = _interopRequireDefault(_antwarConfig);

var _lodash = require("lodash");

var _lodash2 = _interopRequireDefault(_lodash);

var _paths = require("./paths");

var _paths2 = _interopRequireDefault(_paths);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

const BodyContent = (page, allPages) => ({ location }) => render({
  section: getSection(page, allPages),
  config: _antwarConfig2.default,
  page,
  location
});

function getSection(page, allPages) {
  const sectionName = page.sectionName;
  const section = _antwarConfig2.default.paths[sectionName || "/"] || _antwarConfig2.default.paths["/"] || {};

  // Extra check as read-only properties cannot be set. Better to wrap
  // in a function instead?
  if (!section.name) {
    section.name = sectionName;
  }

  // Get all pages of all sections
  section.all = () => getAllSectionPages(allPages);

  // Get pages of the current section or the named one
  section.pages = name => getSectionPages(_antwarConfig2.default, name || sectionName, allPages);

  return section;
}

function getAllSectionPages(allPages) {
  return _lodash2.default.map(_antwarConfig2.default.paths, (path, name) => ({
    url: name,
    path,
    pages: getSectionPages(_antwarConfig2.default, name, allPages)
  }));
}

function getSectionPages(config, name, allPages) {
  return _lodash2.default.filter(_paths2.default.getSectionPages(config, name, allPages), p => p.type === "page");
}

function render(props) {
  let content;

  if (props.page.layout) {
    content = _react2.default.createFactory(props.page.layout)(props);
  } else {
    console.error("Trying to render a page with an unknown type", props);
  }

  // XXX: Refactor config level layout out of the system?
  if (props.config.layout) {
    return _react2.default.createFactory(props.config.layout())(props, content);
  }

  return content;
}

exports.default = BodyContent;