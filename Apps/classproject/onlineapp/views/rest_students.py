from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from onlineapp.models import Student
from onlineapp.serializers import *
from rest_framework.views import APIView
from django.core.exceptions import ObjectDoesNotExist

# @api_view(['GET','POST'])
# def students_list(request, cid, **kwargs):
#     pass

class RestStudentView(APIView):
    def get(self,request,**kwargs):
        if kwargs:
            if ('cid' in kwargs) and not ('sid' in kwargs):
                students = Student.objects.filter(college=kwargs['cid'])
            else:
                students = Student.objects.filter(college=kwargs['cid'],id=kwargs['sid'])
        else:
            return Response(status=status.HTTP_400_BAD_REQUEST)
        if students:
            serializer = StudentDetailsSerializer(students, many=True)
            return Response({'students': serializer.data}, status=status.HTTP_200_OK)
        else:
            return Response(status=status.HTTP_404_NOT_FOUND)

    def post(self, request, **kwargs):
        serializer = StudentDetailsSerializer(data=request.data, context={'c_id':kwargs['cid']})
        if serializer.is_valid():
            serializer.save()
            return Response({'Added student':serializer.data},status=status.HTTP_201_CREATED)
        else:
            return Response(status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, **kwargs):
        if kwargs and ('sid') in kwargs:
            try:
                student = Student.objects.get(id=kwargs['sid'])
                student.delete()
                return Response(status=status.HTTP_200_OK)
            except ObjectDoesNotExist:
                return Response(status=status.HTTP_404_NOT_FOUND)
        else:
            return Response(status=status.HTTP_400_BAD_REQUEST)

    def put(self, request, **kwargs):
        if kwargs and ('sid') in kwargs:
            try:
                student = Student.objects.get(id=kwargs['sid'])
                serializer = StudentDetailsSerializer(data=request.data, instance=student, context={'c_id': kwargs['cid']})
                if serializer.is_valid():
                    serializer.save()
                    return Response({'Modified student': serializer.data}, status=status.HTTP_200_OK)
                else:
                    return Response(status=status.HTTP_400_BAD_REQUEST)
            except ObjectDoesNotExist:
                return Response(status=status.HTTP_404_NOT_FOUND)
        else:
            return Response(status=status.HTTP_400_BAD_REQUEST)
    #
    # def get(self, request, **kwargs):
    #     if 'id' in kwargs:
    #         students = Student.objects.filter(id=kwargs['id'])
    #     else:
    #         college = College.objects.get(id=kwargs["cid"])
    #         students = Student.objects.filter(college=college)
    #     serializer = StudentDetailsSerializer(students, many=True)
    #     return JsonResponse(serializer.data, safe=False)
    #
    # def post(self, request, **kwargs):
    #     college = College.objects.get(id=kwargs["cid"])
    #     student = Student(college=college)
    #     serializer = StudentSerializer(student, data=request.data)
    #     if serializer.is_valid():
    #         serializer.save()
    #     else:
    #         return JsonResponse(serializer.errors, status=400)
    #
    #     data = serializer.data
    #     errors = serializer.errors
    #
    #     if True:
    #         mock1 = MockTest1(student=student)
    #         mockserializer = MockTest1Serializer(mock1, data=request.data['mocktest1'])
    #         if mockserializer.is_valid():
    #             mockserializer.save()
    #             data.update({'mocktest1': mockserializer.data})
    #             return JsonResponse(data, status=201)
    #
    #         errors.update({'mocktest1': mockserializer.errors})
    #
    #     elif serializer.is_valid():
    #         return JsonResponse(data, status=201)
    #     return JsonResponse(errors, status=400)