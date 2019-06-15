from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from onlineapp.models import College
from onlineapp.serializers import *
from django.core.exceptions import ObjectDoesNotExist
from rest_framework.views import APIView
from rest_framework.authentication import SessionAuthentication, BasicAuthentication, TokenAuthentication
from rest_framework.permissions import IsAuthenticated
from onlineapp.models import BearerAuthentication
from rest_framework_simplejwt.authentication import JWTAuthentication

# @api_view(['GET','POST'])
# def college_list(request):
#     if request.method == 'GET':
#         colleges = College.objects.all()
#         serializer = CollegeSerializer(colleges, many=True)
#         if colleges:
#             return Response({"colleges":serializer.data}, status=status.HTTP_200_OK)
#         else:
#             return Response({'Errors':serializer.errors}, status=status.HTTP_404_NOT_FOUND)
#
#     if request.method == 'POST':
#         pass
#         serializer = CollegeSerializer(data=request.data)
#         if serializer.is_valid():
#             serializer.save()
#             return Response({'Added college':serializer.data}, status=status.HTTP_201_CREATED)
#         else:
#             return Response({'Errors':serializer.errors}, status=status.HTTP_400_BAD_REQUEST)
#
#
# @api_view(['GET','POST','PUT','DELETE'])
# def college_details(request, **kwargs):
#
#     try:
#         college = College.objects.filter(**kwargs)
#     except ObjectDoesNotExist:
#         return Response(status=status.HTTP_404_NOT_FOUND)
#
#     if request.method == 'GET':
#
#         serializer = CollegeSerializer(college,many=True)
#         return Response({"colleges":serializer.data}, status=status.HTTP_200_OK)
#
#     if request.method == 'PUT':
#         serializer = CollegeSerializer(data=request.data, instance=College.objects.get(**kwargs))
#         if serializer.is_valid():
#             serializer.save()
#             return Response({"colleges":serializer.data}, status=status.HTTP_200_OK)
#         else:
#             return Response({'Errors': serializer.errors}, status=status.HTTP_400_BAD_REQUEST)
#
#     if request.method=="DELETE":
#         college.delete()
#         return Response(status=status.HTTP_204_NO_CONTENT)


#
# {
#     "refresh": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6MTU2MDU4NzQ4MSwianRpIjoiMDEzYWFkMTYyMzJkNDhiZDkxNThhMGUyNzk1NjUxNGYiLCJ1c2VyX2lkIjoxfQ.D_JkEVKYf1uvJw030O8u_goKArqypnyjSJGq4Fn2bVE",
#     "access": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNTYwNTAxMzgxLCJqdGkiOiJmM2MwODA1Y2U4ZDM0MDExYmU3Njc3ZjQxNTljZWNkNCIsInVzZXJfaWQiOjF9.TpwMwYxqV-DG7rN-U-x8c8IRe346azhLHCcSBb5vgWw"
# }

class RestCollegeView(APIView):
    #for token authentication use Authorization key and values as Token 3bbe095132489f9b95faea0bf6184e3b034ae0ca in header of request
    authentication_classes = (JWTAuthentication, BearerAuthentication, TokenAuthentication, BasicAuthentication, SessionAuthentication)
    permission_classes = (IsAuthenticated,)

    def get(self, request,format=None, **kwargs):
        # content={
        #     'user':request.user
        # }
        if kwargs:
            colleges = College.objects.filter(**kwargs)
        else:
            colleges = College.objects.all()
        if colleges:
            serializer = CollegeSerializer(colleges, many=True)
            return Response({'colleges': serializer.data}, status=status.HTTP_200_OK)
        else:
            return Response(status=status.HTTP_404_NOT_FOUND)

    def post(self, request, **kwargs):
        college = CollegeSerializer(data=request.data)
        if college.is_valid():
            college.save()
            return Response({'Added college':college.data},status=status.HTTP_201_CREATED)
        else:
            return Response(status=status.HTTP_400_BAD_REQUEST)

    def put(self, request, **kwargs):
        if kwargs:
            try:
                college = College.objects.get(**kwargs)
            except ObjectDoesNotExist:
                return Response(status=status.HTTP_404_NOT_FOUND)
            college = CollegeSerializer(data=request.data, instance=College.objects.get(**kwargs))
            if college.is_valid():
                college.save()
                return Response(status=status.HTTP_200_OK)
        return Response(status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, **kwargs):
        if kwargs:
            try:
                college = College.objects.get(**kwargs)
            except ObjectDoesNotExist:
                return Response(status=status.HTTP_404_NOT_FOUND)
            College.objects.get(**kwargs).delete()
            return Response(status=status.HTTP_200_OK)
        else:
            return Response(status=status.HTTP_400_BAD_REQUEST)

