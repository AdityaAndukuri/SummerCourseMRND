from django.contrib.auth.models import User
from rest_framework import serializers
from .models import *

class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model = College
        fields = ('id', 'name', 'acronym', 'location', 'contact')


class StudentSerializer(serializers.ModelSerializer):
    class Meta:
        model = Student
        fields = ('id', 'name', 'dob', 'db_folder', 'college', 'email', 'mocktest1', 'dropped_out')


class MockTest1Serializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        fields = ('id', 'problem1','problem2','problem3','problem4','total')

class StudentDetailsSerializer(serializers.ModelSerializer):
    mocktest1 = MockTest1Serializer(many=False, read_only=False)
    class Meta:
        model = Student
        fields  = ('id', 'name', 'dob', 'db_folder', 'email',  'mocktest1','dropped_out')
    def create(self, validated_data):
        mocktest1_data = validated_data.pop('mocktest1')
        college = College.objects.get(id=self.context['c_id'])
        student=Student.objects.create(college=college, **validated_data)
        MockTest1.objects.create(student=student, **mocktest1_data)
        return student

    def update(self, instance, validated_data):
        mocktest1_data = validated_data.pop('mocktest1')
        mocktest1 = MockTest1.objects.get(student=instance)
        instance.name = validated_data.get('name', instance.name)
        instance.dob = validated_data.get('dob',instance.dob)
        instance.db_folder = validated_data.get('db_folder',instance.db_folder)
        instance.email = validated_data.get('email',instance.email)
        instance.dropped_out = validated_data.get('dropped_out', instance.dropped_out)
        instance.save()
        mocktest1.problem1 = mocktest1_data.get('problem1',mocktest1.problem1)
        mocktest1.problem2 = mocktest1_data.get('problem2', mocktest1.problem2)
        mocktest1.problem3 = mocktest1_data.get('problem3', mocktest1.problem3)
        mocktest1.problem4 = mocktest1_data.get('problem4', mocktest1.problem4)
        mocktest1.total = mocktest1_data.get('total', mocktest1.total)
        mocktest1.save()
        return instance
#
# from rest_framework import serializers
# from onlineapp.models import College, Student, MockTest1
#
#
# class CollegeSerializer(serializers.ModelSerializer):
#     class Meta:
#         model = College
#         fields = ('id', 'name', 'acronym', 'location', 'contact')
#
#
# class StudentSerializer(serializers.ModelSerializer):
#     class Meta:
#         model = Student
#         fields = ('id', 'name', 'email', 'db_folder', 'dropped_out') #, 'college')
#
#
# class MockTest1Serializer(serializers.ModelSerializer):
#     class Meta:
#         model = MockTest1
#         fields = ('problem1', 'problem2', 'problem3', 'problem4', 'total') #, 'student')
#
#
# class StudentDetailsSerializer(serializers.ModelSerializer):
#     mocktest1 = MockTest1Serializer(many=False, read_only=True)
#
#     class Meta:
#         model = Student
#         fields = ('id', 'name', 'email', 'dob', 'db_folder', 'dropped_out', 'mocktest1')