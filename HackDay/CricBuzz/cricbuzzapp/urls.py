from django.contrib import admin
from django.conf import settings
from django.urls import include, path
from rest_framework.authtoken.views import obtain_auth_token
from rest_framework_simplejwt import views as jwt_views
from .views import *

urlpatterns = [
    path('season/<int:sid>/', SeasonView.as_view(), name="season_view"),
    path('', SeasonView.as_view(), name="current_season_view"),
    path('season/<int:sid>/match/<int:mid>/', MatchView.as_view(), name="match_view"),
    path('login/', LoginUserView.as_view(), name="login_view"),
    path('signup/', AddUserView.as_view(), name="signup_view"),
    path('signout/', logout_user, name="signout_view"),
    path('season/<int:year>/points/', PointsView.as_view(), name="points_table")

]
