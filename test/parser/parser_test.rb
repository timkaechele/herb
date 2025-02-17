# frozen_string_literal: true

require_relative "../test_helper"

module Parser
  class ParserTest < Minitest::Spec
    include SnapshotUtils

    test "nil" do
      assert_parsed_snapshot(nil)
    end

    test "empty file" do
      assert_parsed_snapshot("")
    end
  end
end
