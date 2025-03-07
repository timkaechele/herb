# frozen_string_literal: true

require "forwardable"

module Herb
  class ExtractResult
    extend Forwardable

    def_delegators :@buffer, :read

    attr_accessor :buffer

    def initialize(pointer)
      @buffer = LibHerb::Buffer.new(pointer)
    end
  end
end
