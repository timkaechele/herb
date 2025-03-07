# frozen_string_literal: true

require "mkmf"

Dir.chdir(File.expand_path("../..", __dir__)) do
  system("rake templates", exception: true)
end

extension_name = "herb"

include_path = File.expand_path("../../src/include", __dir__)
prism_path = `bundle show prism`.chomp

$VPATH << "$(srcdir)/../../src"

src_files = Dir.glob("#{$srcdir}/../../src/**/*.c").map { |file| file.delete_prefix("../../../../ext/herb/") }.sort
$srcs = ["extension.c", "nodes.c", "error_helpers.c", "extension_helpers.c"] + src_files

append_cppflags("-I#{prism_path}/include")
append_cppflags("-I#{include_path}")

abort("could not find prism.h") unless find_header("prism.h")
abort("could not find herb.h") unless find_header("herb.h")

abort("could not find nodes.h (run `ruby templates/template.rb` to generate the file)") unless find_header("nodes.h")
abort("could not find extension.h") unless find_header("extension.h")
abort("could not find extension_helpers.h") unless find_header("extension_helpers.h")

create_header
create_makefile("#{extension_name}/#{extension_name}")
