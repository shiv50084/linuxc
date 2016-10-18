#!/usr/bin/env python

import os
import sys
from pyinotify import WatchManager, Notifier, \
ProcessEvent,IN_DELETE, IN_CREATE,IN_MODIFY
  
class EventHandler(ProcessEvent):
    def process_IN_CREATE(self, event):
        print  "Create file: %s " %  os.path.join(event.path,event.name)

    def process_IN_DELETE(self, event):
        print  "Delete file: %s " %  os.path.join(event.path,event.name)

    def process_IN_MODIFY(self, event):
        print  "Modify file: %s " %  os.path.join(event.path,event.name)
        full_name = os.path.join(event.path,event.name)
        fd = open(full_name,'r')
        for line in fd.readlines(): 
            print  line
  
def FSMonitor(path='.'):
    wm = WatchManager() 
    mask = IN_DELETE | IN_CREATE | IN_MODIFY
    notifier = Notifier(wm, EventHandler())
    wm.add_watch(path, mask, auto_add=True, rec=True)
    print 'now starting monitor %s' % (path)
    while True:
        try:
            notifier.process_events()
            if notifier.check_events():
                notifier.read_events()
        except KeyboardInterrupt:
            notifier.stop()
            break
  
if __name__ == "__main__":
    try:
        path = sys.argv[1]
    except IndexError:
        print 'Usage: %s monitor_path' % sys.argv[0]
    else:
        FSMonitor(path)

# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
