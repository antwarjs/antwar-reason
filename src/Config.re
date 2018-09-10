type component;

type componentGetter = unit => component;

type page = {
  type_: string,
  fileName: string,
  file: componentGetter,
  layout: componentGetter,
  section,
  url: string,
}
and section = {
  index: componentGetter,
  layout: componentGetter,
  transform: array(page) => array(page),
  url: (~sectionName: string, ~fileName: string) => string,
};

type paths = Js.Dict.t(section);

type template = {file: string};

type config = {
  template,
  output: string,
  layout: componentGetter,
  paths,
};

type environment =
  | Development
  | Production;
