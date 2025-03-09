<script setup>
  import { VPTeamMembers } from "vitepress/theme"

  const creator = {
    avatar: "https://www.github.com/marcoroth.png",
    name: "Marco Roth",
    title: "Creator and Project Lead",
    links: [
      { icon: "github", link: "https://github.com/marcoroth" },
      { icon: "twitter", link: "https://twitter.com/marcoroth_" },
      { icon: "mastodon", link: "https://ruby.social/@marcoroth" },
      { icon: "bluesky", link: "https://bsky.app/profile/marcoroth.dev" },
    ]
  }
</script>

# About Herb

The Herb Project was created and is lead by Marco Roth.

<VPTeamMembers size="small" :members="[creator]" />
