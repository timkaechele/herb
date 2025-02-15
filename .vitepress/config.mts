import { defineConfig } from "vitepress"

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "ERBX",
  description: "ERBX specification and documentation",
  srcDir: "./docs",
  base: "/erbx/",
  themeConfig: {

    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: "Home", link: "/" },
      { text: "Specification", link: "/specification" },
      { text: "Language Bindings", link: "/bindings/ruby/" },
    ],

    sidebar: [
      {
        text: "Specification",
        items: [
          { text: "General", link: "/specification" },
          { text: "HTML", link: "/specification/html" },
          { text: "ERB", link: "/specification/erb" },
          // { text: "Blade", link: "/specification/blade" },
          // { text: "EJS", link: "/specification/ejs" },
          // { text: "Handlebars", link: "/specification/handlebars" },
          // { text: "Jinja", link: "/specification/jinja" },
          // { text: "Liquid", link: "/specification/liquid" },
        ]
      },
      {
        text: "Language Bindings",
        items: [
          {
            text: "Ruby",
            collapsed: true,
            items: [
              { text: "Installation", link: "/bindings/ruby/"},
              { text: "Reference", link: "/bindings/ruby/reference"},
            ]
          },
          {
            text: "JavaScript/Node.js",
            collapsed: true,
            items: [
              { text: "Installation", link: "/bindings/javascript/"},
              { text: "Reference", link: "/bindings/javascript/reference"},
            ]
          },
        ]
      },
    ],

    socialLinks: [
      { icon: "github", link: "https://github.com/marcoroth/erbx" },
      { icon: "twitter", link: "https://twitter.com/marcoroth_" },
      { icon: "mastodon", link: "https://ruby.social/@marcoroth" }
    ]
  }
})
