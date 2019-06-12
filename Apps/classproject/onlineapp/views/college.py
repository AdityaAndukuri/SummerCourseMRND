from django.views import View
from onlineapp.models import *
from onlineapp.forms import *
from django.shortcuts import render,get_list_or_404, get_object_or_404, redirect
from django.urls import resolve
from django.contrib.auth.mixins import *
from django.contrib.auth.decorators import *

def HomeView(request):
    if request.user.is_authenticated:
        return redirect('colleges_list')
    return render(request,template_name='onlineapp/base.html')


class CollegeView(LoginRequiredMixin, View):
    login_url = '/login/'
    def get(self, request, *args, **kwargs):
        if kwargs:
            #college = College.objects.get(**kwargs) #id=pk
            college = get_object_or_404(College, **kwargs)
            students = list(college.student_set.order_by('-mocktest1__total')) #entry_set
            return render(request, "onlineapp/students.html", {'students': students, 'clg_name': college})
        # colleges = College.objects.values('id', 'name', 'acronym')
        colleges = College.objects.all()
        # use jinja templating
        #x = request.user.get_all_permissions()
        return render(request,
                      template_name="onlineapp/colleges.html",
                      context={'colleges': colleges,
                               'title': 'Colleges List',
                               'user_permissions':request.user.get_all_permissions() #after modifictaions are done in admin appp
                               }
                      )

class AddCollegeView(PermissionRequiredMixin, LoginRequiredMixin, View):

    login_url = '/login/'
    permission_required = ('onlineapp.add_college', 'onlineapp.change_college', 'onlineapp.delete_college')
    def get(self, request, **kwargs):
        form = AddCollege()
        if kwargs:
            if resolve(request.path_info).url_name == 'delete_college':
                College.objects.get(**kwargs).delete()
                return redirect('/colleges')
            college = get_object_or_404(College, **kwargs)
            form = AddCollege(instance=college)


        return render(request,template_name="onlineapp/add_college.html",
                      context={'form':form})

    def post(self, request, **kwargs):
        if kwargs:
            if resolve(request.path_info).url_name == 'edit_college':
                college = get_object_or_404(College, **kwargs)
                form = AddCollege(request.POST,instance=college)

        else:
            form=AddCollege(request.POST)
        if form.is_valid():
            form.save()
        else:
            return render(request, template_name="onlineapp/add_college.html",
                          context={'form': form})
        return redirect('colleges_list')


