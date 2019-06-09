import os,django
os.environ.setdefault('DJANGO_SETTINGS_MODULE',"homeproject.settings")
django.setup()

from todoapp.models import *

for i in range(5):
    list = ToDoList(name='List '+str(i))
    list.save()
    for j in range(5):
        ToDoItem(todolist = list,description = 'Description for item '+str(j)+' under List '+str(i)).save()