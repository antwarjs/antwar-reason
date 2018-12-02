module.exports = {
  plugins: [
    require("postcss-import")(),
    require("tailwindcss")("./tailwind.js"),
    require("autoprefixer")({ browsers: ["last 2 versions"] }),
    require("cssnano")(),
  ]
};
