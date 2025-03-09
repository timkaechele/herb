export { Visitor } from "@herb-tools/core"
import { Herb as HerbInstance } from "@herb-tools/core"
import { backend } from "./libherb.js"

/**
 * An instance of the `Herb` class using a browser backend.
 * This loads `libherb` using WebAssembly (WASM).
 */
const Herb = new HerbInstance(backend)

export { Herb }
