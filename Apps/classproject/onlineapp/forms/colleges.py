from onlineapp.models import *
from django import forms

class AddCollege(forms.ModelForm):
    class Meta:
        model = College
        exclude = ['id']
        widgets = {
            'name': forms.TextInput(attrs={'class':'input', 'placeholder':'Enter the college name'}),
            'acronym': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the college acronymm'}),
            'contact': forms.EmailInput(attrs={'class': 'input', 'placeholder': 'Enter the college contact'}),
            'location': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the college location'})

        }