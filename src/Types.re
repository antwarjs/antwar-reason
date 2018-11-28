/*module Section = {*/
  /*type t = {*/
    /*layout: unit => Component.t,*/
    /*index: unit => Component.t,*/
  /*};*/
/*}*/

/*type executionContext = Server | Client | Both;*/

/*module File = {*/
  /*type t;*/
/*};*/

/*module Page = {*/
  /*type t = {*/
    /*file: File.t,*/
    /*url: list(string), [> ["about"], ["about", "1"] <]*/
    /*component: Component.t,*/
    /*executionContext,*/
  /*};*/
/*};*/


/*module SectionPage = {*/
  /*type t;*/
/*};*/

/*module Config = {*/
  /*type t = {  paths: array((string, Page.t)),*/
  /*};*/
/*};*/

/*module ConfigParser = {*/
  /*let parse = (input: string): Config.t = {};*/
/*};*/

/*module Transform = {*/
  /*type transformer = (Page.t) => Page.t;*/
  /*let transform = (config: Config.t, fn: transformer): Config.t = {};*/
/*}*/

/*module Template = {*/
  /*type t;*/
/*};*/

/*module Modules = {*/
  /*type t = Js.t({.});*/
/*};*/
