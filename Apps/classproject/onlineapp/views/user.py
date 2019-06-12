from django.views import View
from django.shortcuts import render, get_list_or_404, get_object_or_404, redirect
from onlineapp.models import *
from onlineapp.forms import *
from django.urls import resolve
from django.contrib.auth import authenticate, login, logout
from django.contrib import messages
from django.contrib.auth.models import User
from django.db.utils import *

def logout_user(request):
    logout(request)
    return redirect('home')

class AddUserView(View):
    def get(self,request,**kwargs):
            if request.user.is_authenticated:
                return redirect('colleges_list')
            user_form = SignupForm()
            return render(request, template_name="onlineapp/signup.html",context={'user_form':user_form})

    def post(self, request, **kwargs):
        user_form = SignupForm(request.POST)
        if user_form.is_valid():
            try:
                user = User.objects.create_user(**user_form.cleaned_data)
                user.save()
                user = authenticate(
                request,
                username=user_form.cleaned_data['username'],
                password = user_form.cleaned_data['password']
                )
                # if user is not None:
                #     login(request, user)
                #     return redirect('colleges_list')
                # else:
                #     messages.error(request, 'Invalid user credentials')
                login(request, user)
                return redirect('colleges_list')
            except Error as e: #IntegrityError
                messages.error(request, e)

        return render(request, template_name="onlineapp/signup.html", context={'user_form': user_form})


class LoginUserView(View):
    def get(self,request,**kwargs):
            if request.user.is_authenticated:
                return redirect('colleges_list')
            login_form = LoginForm()
            return render(request, template_name="onlineapp/login.html",context={'login_form':login_form})
    def post(self, request):
        login_form = LoginForm(request.POST)
        if login_form.is_valid():
            user = authenticate(
                request,
                username=login_form.cleaned_data['username'],
                password=login_form.cleaned_data['password']
            )
            if user is not None:
                login(request, user)
                return redirect('colleges_list')
            else:
                pass
                messages.error(request,'Invalid user credentials')
        return render(request, template_name="onlineapp/login.html", context={'login_form': login_form})
