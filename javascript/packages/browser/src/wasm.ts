import type {
  SerializedLexResult,
  SerializedParseResult,
} from "@herb-tools/core"

// TODO: this is just a stub, replace me with an actual WASM binary
class WASMBinary {
  static lex(source: string) {
    const result: SerializedLexResult = {
      tokens: [],
      source: source,
      warnings: [],
      errors: [],
    }
    return result
  }

  static lexToJson(_source: string) {
    return "{}"
  }

  static parse(source: string) {
    const result: SerializedParseResult = {
      value: {
        type: "AST_DOCUMENT_NODE",
        location: {
          start: { line: 1, column: 1 },
          end: { line: 1, column: 1 },
        },
        children: [],
        errors: [],
      },
      source: source,
      warnings: [],
      errors: [],
    }

    return result
  }

  static extractRuby(source: string) {
    return source
  }

  static extractHtml(source: string) {
    return source
  }

  static version() {
    return "libherb@0.0.1 (wasm)"
  }
}

export default WASMBinary
