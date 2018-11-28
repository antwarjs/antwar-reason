const path = require("path");
const page = require("./utils/page");
const { makeAntwarPaths } = require("./bindings/Antwar.bs");
const renderPage =  require("./utils/render-page")

module.exports = (env) => ({
  apiUrl: "",
  template: {
    file: path.resolve(__dirname, "templates/page.ejs"),
    context: {
      helmet: {}
    }
  },
  render: {
    page: require("./utils/render-page"),
    interactive: require("./utils/render-interactive-page")
  },
  output: "build",
  layout: () => require("./layouts").default,
  paths: makeAntwarPaths()
});
