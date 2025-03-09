---
outline: deep
---

# JavaScript Reference

The `Herb` object exposes a few methods for you to lex, extract and parse HTML+ERB source code.


:::tip Usage

The API remains the same for both packages regardless of whether you imported `Herb` from `@herb-tools/browser` or `@herb-tools/node`.

:::code-group
```js twoslash [Browser]
import { Herb } from "@herb-tools/browser"
```

```js twoslash [Node.js]
import { Herb } from "@herb-tools/node"
```

<br/>

Learn more on [how to install the NPM packages](/bindings/javascript/){target="_self"}

:::

## Herb Reference

The `Herb` class exposes several methods for lexing, extracting, and parsing HTML+ERB source code.

### JavaScript API

`Herb` provides the following key methods:

- **`Herb.lex(source: string): LexResult`**
- **`Herb.lexFile(path: string): Promise<LexResult>`**
- **`Herb.parse(source: string): ParseResult`**
- **`Herb.parseFile(path: string): Promise<ParseResult>`**
- **`Herb.extractRuby(source: string): string`**
- **`Herb.extractHtml(source: string): string`**
- **`Herb.version: string`**


## Lexing

Lexing converts the source code into tokens.

### Example

:::code-group
```js twoslash [javascript]
import { Herb } from "@herb-tools/node"

// ---cut---
const source = "<p>Hello <%= user.name %></p>"
const result = Herb.lex(source)

console.log(result)
//           ^?
```
:::


## Extracting Code

Herb allows you to extract either Ruby or HTML from mixed content.

### Example

:::code-group
```js twoslash [javascript]
import { Herb } from "@herb-tools/node"

// ---cut---
const source = "<p>Hello <%= user.name %></p>"

const ruby = Herb.extractRuby(source)
const html = Herb.extractHtml(source)

console.log(ruby);
// Outputs: "             user.name       "

console.log(html)
// Outputs: "<p>Hello                 </p>"
```
:::

## Parsing

Herb provides a parser to transform HTML+ERB source into an AST (Abstract Syntax Tree).

### Example

:::code-group
```js twoslash [javascript]
import { Herb } from "@herb-tools/node"

// ---cut---
const source = "<p>Hello <%= user.name %></p>"
const result = Herb.parse(source)

console.log(result)
//           ^?
```
:::

## AST Traversal

Herb supports AST traversal using visitors.

### Example

:::code-group
```js twoslash [javascript]
import { Herb } from "@herb-tools/node"

// ---cut---
import { Visitor } from "@herb-tools/node"
// import { Visitor } from "@herb-tools/browser"

class TextNodeVisitor extends Visitor {
  visitHTMLTextNode(node) {
    console.log("HTML TextNode", node.content);
  }
}

const visitor = new TextNodeVisitor()
const result = Herb.parse("<p>Hello <%= user.name %></p>")

result.visit(visitor)
```
:::

This allows you to analyze parsed HTML+ERB programmatically.
