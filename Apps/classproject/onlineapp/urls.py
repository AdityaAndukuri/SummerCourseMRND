from django.contrib import admin
from django.conf import settings
from django.urls import include, path
from .views import *

urlpatterns = [
    path('colleges/',CollegeView.as_view(), name="colleges_list"), #as view is executed when the server starts not during the runtime
    #path('hello/', views.hello_world),
    # path('foo/', views.foo),
    path('colleges/<int:id>/', StudentView.as_view(),  name='student_details'),
    path('colleges/<int:id>/add_student', AddStudentView.as_view(),  name='add_student'),
    #path('colleges/<int:pk>/', StudentView.as_view(),  name='students_url')
    #path('colleges/<int:pk>/',CollegeView.as_view(), name="student_details"),
    #path('colleges/<str:acronym>/',CollegeView.as_view(), name="student_details"),
    path('colleges/add_college',AddCollegeView.as_view(), name="add_college"),
    path('colleges/<int:id>/edit', AddCollegeView.as_view(), name="edit_college"),
    path('colleges/<int:id>/delete', AddCollegeView.as_view(), name="delete_college"),
    path('colleges/<int:id>/student/edit', AddStudentView.as_view(), name="edit_student"),
    path('colleges/<int:id>/student/delete', AddStudentView.as_view(), name="delete_student"),
    path('signup/', AddUserView.as_view(), name='signup'),
    path('login/', LoginUserView.as_view(), name='login'),
    path('logout/', logout_user, name='logout'),
    path('',HomeView,name='home'),
    # path('api/v1/colleges/',rest_colleges.college_list,name="rest_college_list"),
    # path('api/v1/colleges/<int:id>',rest_colleges.college_details),
    path('api/v1/colleges/', RestCollegeView.as_view(),name="rest_college_list"),
    path('api/v1/colleges/<int:id>',RestCollegeView.as_view(),name="rest_college_details"),
    path('api-auth/', include('rest_framework.urls')),
    path('api/v1/colleges/<int:cid>/students/<int:sid>', RestStudentView.as_view(),name="rest_students_list"),
    path('api/v1/colleges/<int:cid>/students/', RestStudentView.as_view(),name="rest_students_details"),
    #path('api/v1/colleges/<int:id>',RestCollegeView.as_view(),name="rest_college_details"),


]

