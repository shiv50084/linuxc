incdir = include_directories('../include')
links = ['-L../lib/dynamic/build',
	'-L../lib/static/build',
	'-ltest_d',
	'-ltest_s'
	]

executable('testapp', 'sharelib.c', link_args : links,
	include_directories : incdir)
