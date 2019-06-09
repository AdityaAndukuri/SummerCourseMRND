from django.contrib import admin

# Register your models here.

from .models import College, Student, MockTest1, Teacher
admin.site.register(College)  #to register model to admin app
admin.site.register(Student)
admin.site.register(MockTest1)
admin.site.register(Teacher)