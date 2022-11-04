gtk_test_sources = [
  'main.c',
  'gtk-test-application.c',
  'gtk-test-row.c',
  'gtk-test-window.c',
]

gtk_test_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1'),
]

gtk_test_sources += gnome.compile_resources('gtk-test-resources',
  'gtk-test.gresource.xml',
  c_name: 'gtk_test'
)

executable('gtk-test', gtk_test_sources,
  dependencies: gtk_test_deps,
       install: true,
)
