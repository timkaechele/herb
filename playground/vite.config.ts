import express from "express"

import { defineConfig } from "vite"
import { Herb } from "@herb-tools/node"

import type { Request, Response } from "express"

export default defineConfig({
  plugins: [
    {
      name: "api-server",
      configureServer(server) {
        const app = express()

        app.use(express.text({ type: "*/*" }))

        app.post("/api/analyze", (request: Request, response: Response) => {
          try {
            const source = request.body

            const result = {
              string: Herb.parse(source).value.inspect(),
              json: JSON.stringify(Herb.parse(source).value, null, 2),
              lex: Herb.lex(source).value.inspect(),
              ruby: Herb.extractRuby(source),
              html: Herb.extractHtml(source),
            }

            return response.json(result)
          } catch (e) {
            console.error("Error in API route:", e)
            return response.status(500).json({
              error: e.message || "An error occurred during parsing"
            })
          }
        })

        server.middlewares.use(app)
      }
    }
  ]
})
