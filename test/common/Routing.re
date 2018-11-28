/*
    This module expresses the Antwar routes and exposes
    a variant type `route` for App usage.

    It exposes a function `makeAntwarPaths()`, which is
    used in the `antwar.config.js` file.

    Naming convention for Routes & Paths:
    -------------------------------------

    Example: /about
    |
    |-> Pathname: /about
    |-> Path: about
    |-> route: About
 */

/*
    This gives the rendering engine more meta information
    Which is utilized in the Layout & Meta components.
 */
[@bs.deriving abstract]
type meta = {
  [@bs.optional]
  title: string,
  [@bs.optional]
  keywords: array(string),
  [@bs.optional]
  description: string,
};

[@bs.module] external page: (string, meta) => Js.t({.}) = "../utils/page";

type route =
  | Index
  | Typography
  | Colors
  | Buttons
  | Test
  | NotFound;

let pathnameToRoute = (pathname: string): route =>
  switch (pathname) {
  | "/" => Index
  | "/typography" => Typography
  | "/colors" => Colors
  | "/buttons" => Buttons
  | _ => NotFound
  };

let routeToPath = (route: route): string =>
  switch (route) {
  | Index => ""
  | Typography => "typography"
  | Colors => "colors"
  | Buttons => "buttons"
  | Test => "test"
  | NotFound => "404"
  };

let href = (~anchor: option(string)=?, route: route): string =>
  switch (anchor) {
  | None => "/" ++ routeToPath(route)
  | Some(anchor) => "/" ++ routeToPath(route) ++ "#" ++ anchor
  };

/* Makes sure an value is anchorable */
let anchorize = text => Js.String.replaceByRe([%re "/ /g"], "_", text);

type routeMapping = (route, string, meta);

/*
    These routes will be mapped by Antwar
    Whenever you need a new route, add it here
 */
let routeFileMappings: list(routeMapping) = [
  /*(Index, "page_index.gen.js", meta()),*/
  /*(Typography, "page_typography.gen.js", meta()),*/
  /*(Colors, "page_colors.gen.js", meta()),*/
  /*(Buttons, "page_buttons.gen.js", meta()),*/
  (Index, "test.js", meta()),
  (Test, "test.js", meta()),
  /*(NotFound, "page_404.gen.js", meta()),*/
];
