from django.views import View
from django.shortcuts import render, get_list_or_404, get_object_or_404, redirect
from onlineapp.models import *
from onlineapp.forms import *
from django.urls import resolve
from django.contrib.auth.mixins import *

class StudentView(LoginRequiredMixin,View):
    login_url = '/login/'
    def get(self,request, **kwargs):
        # students = Student.objects.filter(college__id=kwargs['pk'])
        # #return render(request, "onlineapp/students.html", {'students': students, 'clg_name':kwargs['clg_name']})
        # clg_name = College.objects.values('name').get(id=kwargs['pk'])
        # return render(request, "onlineapp/students.html", {'students': students, 'clg_name': clg_name})
        college = get_object_or_404(College, **kwargs)
        students = list(college.student_set.order_by('-mocktest1__total'))  # entry_set
        return render(request, "onlineapp/students.html", {'students': students, 'clg_name': college})

class AddStudentView(PermissionRequiredMixin,LoginRequiredMixin, View):
    permission_required = ('onineapp.add_student', 'onlineapp.change_student', 'onlineapp.delete_student')
    login_url = '/login'
    def get(self, request, **kwargs):
        s_form = StudentForm()
        m_form = MockTest1Form()
        if kwargs:
            if resolve(request.path_info).url_name == 'delete_student':
                student = Student.objects.get(**kwargs)
                student.delete() #deletes only primary key
                kwargs['id'] = student.college.id
                return redirect('student_details', **kwargs)
            if resolve(request.path_info).url_name == 'edit_student':
                student = get_object_or_404(Student, **kwargs)
                if MockTest1.objects.filter(student=student).count():
                    mocktest1 = MockTest1.objects.get(student=student)
                    m_form = MockTest1Form(instance=mocktest1)
                else:
                    m_form = MockTest1Form()

                s_form = StudentForm(instance=student)



        return render(request,template_name="onlineapp/add_student.html",
                      context={'s_form':s_form, 'm_form':m_form})


    def post(self, request, **kwargs):
        # if kwargs:
        #     if resolve(request.path_info).url_name == 'edit_college':
        #         college = get_object_or_404(College, **kwargs)
        #         form = AddCollege(request.POST,instance=college)
        #
        # else:
        if kwargs:
            if resolve(request.path_info).url_name == 'edit_student':
                student = get_object_or_404(Student, **kwargs)
                s_form = StudentForm(request.POST,instance=student)
                total_marks = 0
                for i in range(1, 5):
                    total_marks += int(request.POST['problem' + str(i)])
                if MockTest1.objects.filter(student=student).count():
                    mocktest1 = MockTest1.objects.get(student=student)
                    mock = MockTest1Form(instance=mocktest1)
                else:
                    mock = MockTest1(student=student)
                mock.total = total_marks
                m_form = MockTest1Form(request.POST, instance=mock)
                if s_form.is_valid():
                    s_form.save()
                else:
                    return render(request, template_name="onlineapp/add_student.html",
                                  context={'s_form': s_form, 'm_form': m_form})
                if m_form.is_valid():
                    m_form.save()
                else:
                    return render(request, template_name="onlineapp/add_student.html",
                                  context={'s_form': s_form, 'm_form': m_form})
            else:
                college_obj = get_object_or_404(College, **kwargs)
                student = Student(college=college_obj)
                s_form = StudentForm(request.POST, instance=student)
                m_form = MockTest1Form(request.POST)
                total_marks = 0
                for i in range(1, 5):
                    total_marks += int(request.POST['problem' + str(i)])
                if s_form.is_valid():
                    s_form.save()

                else:
                    return render(request, template_name="onlineapp/add_student.html",
                                  context={'s_form': s_form, 'm_form': m_form})
                mock = MockTest1(student=student, total=total_marks)
                m_form = MockTest1Form(request.POST, instance=mock)
                if m_form.is_valid():
                    m_form.save()
                else:
                    return render(request, template_name="onlineapp/add_student.html",
                                  context={'s_form': s_form, 'm_form': m_form})

        else:
            pass
        kwargs['id'] = student.college.id
        return redirect('student_details', **kwargs)

#
# <span class="navbar-item">
#               <a class="button is-primary is-inverted">
#
#                 <span>logout</span>
#               </a>
#             </span>