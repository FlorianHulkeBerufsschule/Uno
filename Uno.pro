TEMPLATE = subdirs

SUBDIRS += \
    Client \
    Server \
    Shared

Client.depends = Shared
Server.depends = Shared
