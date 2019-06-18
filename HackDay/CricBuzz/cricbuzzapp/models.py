from django.db import models

# Create your models here.


class Season(models.Model):
    year =models.IntegerField(unique=True, blank=False, null = False)

    def __str__(self):
        return self.year


class Match(models.Model):
    match_id = models.IntegerField(primary_key=True, unique=True, blank=False, null = False)
    city = models.CharField(max_length=128, default="None", blank=True, null = True)
    date = models.DateField(null=True, default="1998-09-22", blank=True)
    team1 =models.CharField(max_length=128, default="None", blank=True, null = True)
    team2 =models.CharField(max_length=128, default="None", blank=True, null = True)
    toss_winner =models.CharField(max_length=128, default="None", blank=True, null = True)
    toss_decision =models.CharField(max_length=128, default="None", blank=True, null = True)
    result =models.CharField(max_length=128, default="None", blank=True, null = True)
    dl_applied =models.IntegerField( blank=True, null = True)
    winner =models.CharField(max_length=128, default="None", blank=True, null = True)
    win_by_runs =models.IntegerField( blank=True, null = True)
    win_by_wickets =models.IntegerField( blank=True, null = True)
    player_of_the_match =models.CharField(max_length=128, default="None", blank=True, null = True)
    venue =models.CharField(max_length=128, default="None", blank=True, null = True)
    umpire1 =models.CharField(max_length=128, default="None", blank=True, null = True)
    umpire2 =models.CharField(max_length=128, default="None", blank=True, null = True)
    umpire3 =models.CharField(max_length=128, default="None", blank=True, null = True)

    season = models.ForeignKey(Season, on_delete=models.CASCADE)


class Innings(models.Model):
    match = models.ForeignKey(Match, on_delete=models.CASCADE)
    innings_no = models.IntegerField()
    batting_team = models.CharField(max_length=128, default="None", blank=True, null = True)
    bowling_team = models.CharField(max_length=128, default="None", blank=True, null = True)


class Over(models.Model):
    innings = models.ForeignKey(Innings, on_delete=models.CASCADE)
    bowler = models.CharField(max_length=128, default="None", blank=True, null = True)
    over_no = models.IntegerField()
    is_super_over = models.IntegerField()


class Delivery(models.Model):
    over = models.ForeignKey(Over, on_delete = models.CASCADE)
    ball_no = models.IntegerField()
    batsman = models.CharField(max_length=128, default="None", blank=True, null = True)
    non_striker = models.CharField(max_length=128, default="None", blank=True, null = True)
    wide_runs = models.IntegerField()
    bye_runs = models.IntegerField()
    legbye_runs = models.IntegerField()
    noball_runs = models.IntegerField()
    penalty_runs = models.IntegerField()
    batsman_runs = models.IntegerField()
    extra_runs = models.IntegerField()
    total_runs = models.IntegerField()
    player_dismissal = models.CharField(max_length=128,default="None", blank=True, null = True)
    dismissal_kind = models.CharField(max_length=128, blank=True,default="None", null = True)
    fielder = models.CharField(max_length=128, blank=True,default='None', null = True)


class PointsTable(models.Model):
    team = models.CharField(max_length=128,default="None", blank=True, null = True)
    played = models.IntegerField()
    won = models.IntegerField()
    lost = models.IntegerField()
    no_result = models.IntegerField()
    points = models.IntegerField()
    season = models.ForeignKey(Season, on_delete=models.CASCADE)

