# frozen_string_literal: true

require_relative "../test_helper"

module Parser
  class BooleanAttributesTest < Minitest::Spec
    include SnapshotUtils

    test "boolean attribute" do
      assert_parsed_snapshot(%(<input required />))
    end

    test "boolean attribute without whitespace" do
      assert_parsed_snapshot(%(<input required/>))
    end

    test "boolean attribute without whitespace and without self-closing tag" do
      assert_parsed_snapshot(%(<input required>))
    end

    test "boolean attribute followed by regular attribute" do
      assert_parsed_snapshot(%(<input required id="input"/>))
    end

    test "boolean attribute after regular attribute" do
      assert_parsed_snapshot(%(<input id="input" required />))
    end

    test "boolean attribute surrounded by regular attributes" do
      assert_parsed_snapshot(%(<input class="classes" required id="ids"/>))
    end
  end
end
