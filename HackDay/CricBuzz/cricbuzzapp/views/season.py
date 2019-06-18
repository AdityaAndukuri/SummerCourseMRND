from django.views import View
from django.shortcuts import render
from cricbuzzapp.models import *
from django.core.paginator import Paginator
from django.db.models import Count,Max,Q,Sum
from django.contrib.auth.mixins import LoginRequiredMixin, PermissionRequiredMixin

class SeasonView(View):
    def get(self, request, **kwargs):
        pass
        if kwargs:
            season = Season.objects.get(year=kwargs['sid'])
        else:
            season = Season.objects.get(year=2019)
        matches = Match.objects.filter(season=season)
        seasons = Season.objects.values('year')
        paginator = Paginator(matches, 8)  # Show 8 matches per page
        page = request.GET.get('page')
        matches = paginator.get_page(page)
        return render(request,
                          template_name="cricbuzzapp/season.html",
                          context={'season':season.year,'matches':matches,'seasons':seasons})

class PointsView(View):
    def get(self, request, **kwargs):
        if kwargs:
            season = Season.objects.get(year=kwargs['year'])
        else:
            season = Season.objects.get(year=2019)
        points_table = PointsTable.objects.filter(season=season).order_by('-points')
        seasons = Season.objects.values('year')
        return render(request,
                      template_name='cricbuzzapp/points.html',
                      context={'season':season.year, 'points_table':points_table,'seasons':seasons})

class MatchView(LoginRequiredMixin, View):
    login_url = '/login/'
    def get(self, request, **kwargs):
        if kwargs:
            match = Match.objects.get(match_id=kwargs['mid'])
            season = Season.objects.get(year=kwargs['sid'])
            #matches = Match.objects.filter(season=season)
            innings = list(Innings.objects.filter(match=match))
            overs = []
            top_3_bat_ing1 = Delivery.objects.filter(over__innings__match = match, over__innings=innings[0]).values('batsman').annotate(score=Count('batsman_runs')).order_by('-score')[:3]
            top_3_bowl_ing1 = Delivery.objects.filter(Q(dismissal_kind = 'caught')|Q(dismissal_kind = 'bowled')|Q(dismissal_kind='lbw'), over__innings__match = match, over__innings=innings[0]).values('over__bowler').annotate(wickets=Count('over__bowler')).order_by('-wickets')[:3]
            for bat in top_3_bat_ing1:
                print(bat)
            for bowl in top_3_bowl_ing1:
                print(bowl)
            top_3_bat_ing2 = Delivery.objects.filter(over__innings__match=match, over__innings=innings[1]).values(
                'batsman').annotate(score=Count('batsman_runs')).order_by('-score')[:3]
            top_3_bowl_ing2 = Delivery.objects.filter(
                Q(dismissal_kind='caught') | Q(dismissal_kind='bowled') | Q(dismissal_kind='lbw'),
                over__innings__match=match, over__innings=innings[1]).values('over__bowler').annotate(
                wickets=Count('*')).order_by('-wickets')[:3]
            score_ing1= Delivery.objects.filter(over__innings__match=match, over__innings=innings[0]).values('total_runs', 'extra_runs', 'player_dismissal').aggregate(score=Sum('total_runs'),extra_score = Sum('extra_runs'),wickets=Count('player_dismissal'))
            score_ing2 = Delivery.objects.filter(over__innings__match=match, over__innings=innings[1]).values(
                'total_runs', 'extra_runs', 'player_dismissal').aggregate(score=Sum('total_runs'),
                                                                            extra_score=Sum('extra_runs'),
                                                                           wickets=Count('player_dismissal'))
            print(score_ing1)
            print(score_ing2)
            for bat in top_3_bat_ing2:
                print(bat)
            for bowl in top_3_bowl_ing2:
                print(bowl)
            return render(request,
                          template_name="cricbuzzapp/match.html",
                          context={'score1':score_ing1,'score2':score_ing2,'inning1':innings[0],'inning2':innings[1], 'season':season.year,'match':match,"top_3_bat_ing1":top_3_bat_ing1,"top_3_bat_ing2":top_3_bat_ing2, "top_3_bowl_ing1":top_3_bowl_ing1, "top_3_bowl_ing2":top_3_bowl_ing2})