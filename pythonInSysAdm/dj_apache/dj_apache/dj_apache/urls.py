from django.conf.urls import patterns, include, url

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
	(r'^$', 'dj_apache.logview.views.list_files'),
	(r'^viewlog/(?P<sortmethod>.*?)/(?P<filename>.*?)/$',
	'dj_apache.logview.views.viewLog'),
    # Examples:
    # url(r'^$', 'dj_apache.views.home', name='home'),
    # url(r'^dj_apache/', include('dj_apache.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    # url(r'^admin/', include(admin.site.urls)),
)
