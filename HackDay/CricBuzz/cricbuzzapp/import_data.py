
import os
import sys
import openpyxl
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'CricBuzz.settings')
import django
django.setup()



from cricbuzzapp.models import *

def main():
    workbook = openpyxl.load_workbook("matches.xlsx")
    worksheet = workbook.get_active_sheet()
    flag = 0
    data = []
    seasons = set()
    for row in worksheet.rows:
        if not flag:
            flag = 1
            continue
        match = [cell.value for cell in row]
        if(match[1]):
            if match[1] not in seasons:
                seasons.add(match[1])
                s = Season(year=match[1])
                s.save()
            data.append(match)
            #match[3]=match[3].replace('/','-')
            if '/' in match[3]:
                date = match[3].split('/')
                date[2]='20'+date[2]
                match[3] = '-'.join(date[::-1])
            #print(match)
            #print(seasons)
            Match(match_id=match[0],season=s,city=match[2],date=match[3],team1=match[4],team2=match[5],toss_winner=match[6],toss_decision=match[7],result=match[8],dl_applied=match[9],winner=match[10],win_by_runs=match[11],win_by_wickets=match[12],player_of_the_match=match[13],venue=match[14],umpire1=match[15],umpire2=match[16],umpire3=match[17]).save()
        #print(match)
        #print(seasons)
    # for x in seasons:
    #     Season(year=x).save()

def deli():
    workbook = openpyxl.load_workbook("deliveries.xlsx")
    worksheet = workbook.get_active_sheet()
    flag = 0
    data = []
    innings_flag = 0
    overs = set()
    for row in worksheet.rows:
        if not flag:
            flag = 1
            continue
        #print(data)
        delivery = [cell.value for cell in row]
        match = Match(match_id=delivery[0])
        if innings_flag==0 and delivery[1]==1:
            overs=set()
            inning = Innings(match=match, innings_no=delivery[1],batting_team=delivery[2],bowling_team=delivery[3])
            inning.save()
            innings_flag=1
        elif innings_flag == 1 and delivery[1]==2:
            overs=set()
            inning = Innings(match=match, innings_no=delivery[1], batting_team=delivery[2], bowling_team=delivery[3])
            inning.save()
            innings_flag = 0
        if delivery[4] not in overs:
            over = Over(innings=inning,bowler=delivery[8],over_no=delivery[4],is_super_over=delivery[9])
            overs.add(delivery[4])
            over.save()
        delivery_ball = Delivery(over=over)
        delivery_ball.ball_no=delivery[5]
        delivery_ball.batsman=delivery[6]
        delivery_ball.non_striker=delivery[7]
        delivery_ball.wide_runs=delivery[10]
        delivery_ball.bye_runs=delivery[11]
        delivery_ball.legbye_runs=delivery[12]
        delivery_ball.noball_runs=delivery[13]
        delivery_ball.penalty_runs=delivery[14]
        delivery_ball.batsman_runs=delivery[15]
        delivery_ball.extra_runs=delivery[16]
        delivery_ball.total_runs=delivery[17]
        delivery_ball.player_dismissal=delivery[18]
        delivery_ball.dismissal_kind=delivery[19]
        delivery_ball.fielder=delivery[20]
        delivery_ball.save()




    print('helli')

def points():
    rows = {}
    seasons = Season.objects.all()
    for season in seasons:
        #print(season)
        matches = Match.objects.filter(season=season)
        rows={}
        for match in matches:
            #print(match.season.year)
            if match.result in ['normal', 'tie']:
                team1 = match.winner
                if match.winner == match.team1:
                    team2 = match.team2
                else:
                    team2 = match.team1
                if team1 not in rows:
                    rows[team1] = [1, 1, 0, 0, 2]
                else:
                    rows[team1][0] += 1
                    rows[team1][1] += 1
                    rows[team1][4] += 2
                if team2 not in rows:
                    rows[team2]=[1,0,1,0,0]
                else:
                    rows[team2][0]+=1
                    rows[team2][2]+=1
            else:
                team1=match.team1
                team2=match.team2
                if team1 not in rows:
                    rows[team1]=[1,0,0,1,1]
                else:
                    rows[team1][0]+=1
                    rows[team1][3]+=1
                    rows[team1][4]+=1
                if team2 not in rows:
                    rows[team2]=[1,0,0,1,1]
                else:
                    rows[team2][0]+=1
                    rows[team2][3]+=1
                    rows[team2][4]+=1
        print(season.year,rows)
        for row in rows:
            PointsTable(season=season, team=row, played = rows[row][0], won = rows[row][1], lost = rows[row][2], no_result = rows[row][3], points = rows[row][4]).save()


if __name__=="__main__":
    #main()
    #deli()
    points()