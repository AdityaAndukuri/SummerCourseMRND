from onlineapp.models import *
from django import forms


class StudentForm(forms.ModelForm):
    class Meta:
        model = Student
        exclude = ['id', 'college', 'dob']
        widgets = {
            'name': forms.TextInput(attrs={
                'class':'input',
                'placeholder':'Enter Student name'
            }),
            'email': forms.EmailInput(attrs={
               'class':'input',
                'placeholder': 'Enter Student email'
            }),
            'db_folder':forms.TextInput(attrs={
                'class':'input',
                'placeholder':'Enter Student database name'
            }),
            'dropped_out':
                forms.CheckboxInput()
    }

class MockTest1Form(forms.ModelForm):
    class Meta:
        model = MockTest1
        exclude = ['student', 'total', 'id']
        widgets = {
            'problem1':forms.NumberInput(attrs={
                'class': 'input',
                'placeholder': 'Enter problem1 marks'
            }),
            'problem2': forms.NumberInput(attrs={
                'class': 'input',
                'placeholder': 'Enter problem2 marks'
            }),
            'problem3': forms.NumberInput(attrs={
                'class': 'input',
                'placeholder': 'Enter problem3 marks'
            }),
            'problem4': forms.NumberInput(attrs={
                'class': 'input',
                'placeholder': 'Enter problem4 marks'
            }),

        }