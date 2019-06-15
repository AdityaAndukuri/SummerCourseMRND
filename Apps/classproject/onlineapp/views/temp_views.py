from onlineapp.models import *
from onlineapp.models import *
from django.http import HttpResponse

def my_firts_view(request):
    return HttpResponse("my first response\n")