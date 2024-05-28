import { defineConfig } from "vitepress"

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "ERBx",
  description: "ERBx specification and documentation",
  srcDir: "./docs",
  themeConfig: {

    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: "Home", link: "/" },
      { text: "Specification", link: "/specification" },
    ],

    sidebar: [
      {
        text: "Specification",
        items: [
          { text: "General", link: "/specification" },
          { text: "HTML", link: "/specification/html" },
          { text: "ERB", link: "/specification/erb" },
          { text: "EJS", link: "/specification/ejs" },
          { text: "Handlebars", link: "/specification/handlebars" },
          { text: "Jinja", link: "/specification/jinja" },
        ]
      }
    ],

    socialLinks: [
      { icon: "github", link: "https://github.com/marcoroth/erbx" },
      { icon: "twitter", link: "https://twitter.com/marcoroth_" },
      { icon: "mastodon", link: "https://ruby.social/@marcoroth" }
    ]
  }
})
