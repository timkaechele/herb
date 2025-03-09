const path = require("path")
const binary = require("@mapbox/node-pre-gyp")

const { Herb: HerbInstance, Visitor } = require("@herb-tools/core")
const { createBackend } = require("./libherb.js")

const packagePath = path.resolve(__dirname, "../package.json")
const libherbPath = binary.find(packagePath)

const libHerbBinary = require(libherbPath)
const backend = createBackend(libHerbBinary)

/**
 * An instance of the `Herb` class using a Node.js backend.
 * This loads `libherb` in a Node.js C++ native extension.
 */
const Herb = new HerbInstance(backend)

module.exports = {
  Herb: Herb,
  Visitor: Visitor,
}
