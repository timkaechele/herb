import { HerbError, HerbWarning } from "./nodes.js"

export class Result {
  readonly source: string
  readonly warnings: HerbWarning[]
  readonly errors: HerbError[]

  constructor(
    source: string,
    warnings: HerbWarning[] = [],
    errors: HerbError[] = [],
  ) {
    this.source = source
    this.warnings = warnings || []
    this.errors = errors || []
  }

  success(): boolean {
    return false
  }

  failed(): boolean {
    return true
  }
}
