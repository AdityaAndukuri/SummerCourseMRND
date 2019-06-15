from django.db import models
from rest_framework.authentication import TokenAuthentication
# Create your models here.

class College(models.Model):
    name = models.CharField(max_length=128, unique=True, blank=False, null=False)
    location = models.CharField(max_length=64)
    acronym = models.CharField(max_length=8)
    contact = models.EmailField()

    def __str__(self):
        return self.acronym

class Student(models.Model):
    name = models.CharField(max_length=128)
    dob = models.DateField(null=True, default="1998-09-22")
    email = models.EmailField()
    db_folder = models.CharField(max_length=50)
    dropped_out = models.BooleanField(default=False)

    college = models.ForeignKey(College, on_delete=models.CASCADE) #

    def __str__(self):
        return self.name


class MockTest1(models.Model):
    problem1 = models.IntegerField()
    problem2 = models.IntegerField()
    problem3 = models.IntegerField()
    problem4 = models.IntegerField()
    total = models.IntegerField()

    student = models.OneToOneField(Student, on_delete=models.CASCADE)

    def __str__(self):
        return f"Student {self.student.name} marks"


class Teacher(models.Model):
    name = models.CharField(max_length=42)
    college = models.ForeignKey(College, on_delete=models.CASCADE)



class BearerAuthentication(TokenAuthentication, models.Model):
    '''
    Simple token based authentication using utvsapitoken.

    Clients should authenticate by passing the token key in the 'Authorization'
    HTTP header, prepended with the string 'Bearer '.  For example:

    Authorization: Bearer 956e252a-513c-48c5-92dd-bfddc364e812
    '''
    keyword = 'Bearer'