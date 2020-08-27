incdir = include_directories('../include')

# using linkwith instead of link args
linkwith = [slib, dlib]

executable('testapp', 'sharelib.c', link_with : linkwith,
	include_directories : incdir)
