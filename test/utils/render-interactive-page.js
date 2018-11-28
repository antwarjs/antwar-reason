const React = require("react");
const ReactDOMServer = require("react-dom/server");

module.exports = ({component, props}) => {
  console.log("FOOOOOOOOOOOOOOOOOOOOOOOOOO");
  return ReactDOMServer.renderToStaticMarkup(
    React.createElement(component, props)
  );
}
