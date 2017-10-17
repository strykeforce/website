# coding: utf-8

Gem::Specification.new do |spec|
  spec.name          = "sf_master_theme"
  spec.version       = "0.0.0"
  spec.authors       = ["Stryke Force"]
  spec.email         = [""]

  spec.summary       = %q{A Master Theme for the Stryke Force Robotics Website.}
  spec.homepage      = "https://strykeforce.org"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").select { |f| f.match(%r{^(assets|_layouts|_includes|_sass|LICENSE|README)}i) }

  spec.add_development_dependency "jekyll", "~> 3.3"
  spec.add_development_dependency "bundler", "~> 1.12"
  spec.add_development_dependency "rake", "~> 10.0"
end
