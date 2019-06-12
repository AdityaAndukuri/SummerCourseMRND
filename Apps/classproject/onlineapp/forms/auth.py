from django import forms

class LoginForm(forms.Form):
    username = forms.CharField(
        required=True,
        widget = forms.TextInput(attrs={
            'class':'input',
            'placeholder':'Enter Username'
        })
    )
    password = forms.CharField(
        required=True,
        widget = forms.PasswordInput(attrs={
            'class':'input',
            'placeholder':'Enter Password'
        }
        )
    )

class SignupForm(forms.Form):
    first_name = forms.CharField(
        required=True,
        max_length=30,
        widget=forms.TextInput(attrs={
            'class':'input',
            'placeholder':'Enter first name'
        })
    )
    last_name = forms.CharField(
        required=True,
        max_length=30,
        widget=forms.TextInput(attrs={
            'class': 'input',
            'placeholder': 'Enter last name'
        })
    )
    username = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs={
            'class': 'input',
            'placeholder': 'Enter Username'
        })
    )
    password = forms.CharField(
        required=True,
        max_length=30,
        widget=forms.PasswordInput(attrs={
            'class': 'input',
            'placeholder': 'Enter Password'
        }
        )
    )


