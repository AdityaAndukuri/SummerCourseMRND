import os
import sys
# py manage.py shell_plus --print-sql

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'classproject.settings')

import django
django.setup()
from onlineapp.models import *
from django.db.models import Count,Max

#retrieve all colleges
c = College.objects.all()  #limit is 21 by default last element is ... reprsent there exists more records to be fetched adn also the query is not executed now , just a query set is returned
print(c)  #now the query is called and records re fetched
print(c)
print(c)
for x in c:
    print(sys.getsizeof(x))
    print(x.name, x.location, x.acronym, x.contact)

#count of all colleges

print(len(c))

print(College.objects.count())

#extract only acronym and contact

c = College.objects.values('acronym', 'contact')

for i in range(len(c)):
    print(c[i])

c = College.objects.values_list('acronym', 'contact')
print(c)
for i in range(len(c)):
    print(c[i])

#colleges count in vizag
print(College.objects.filter(location='Vizag').count())
print(College.objects.values('location').filter(location='vizag').count())

#sort by acronym

c  = College.objects.order_by('acronym') #ascending
for x in c:
    print(x.name, x.location, x.acronym, x.contact,sep='\t')

c  = College.objects.order_by('-acronym')[:5] #descending
for x in c:
    print(x.name, x.location, x.acronym, x.contact,sep='\t')

#bottom five in descending order
c=College.objects.order_by('-acronym').reverse()[:5]
for x in c:
    print(x.name, x.location, x.acronym, x.contact,sep='\t')


#colleges count at each location
print(College.objects.values('location'))

print(College.objects.values_list('location').annotate(clg_count=Count('location'))) #similar to group by

print(College.objects.values('contact').annotate(clg_count=Count('location'))) #similar to group by


#sort wrt to no of colleges at each location

                                #used for group by                  #aggrerate function
print(College.objects.values_list('location').annotate(clg_count=Count('*')).order_by('clg_count')) #similar to group by

#get colleges names which has atleast one drop out students

ids = Student.objects.filter(dropped_out=1).values('college__name').distinct()
print(ids)
#print(College.objects.filter(id in ids))

#print college names with count of students

print(Student.objects.values('college__name').annotate(cnt=Count('id'))) # __ to refer the fields in parent

#students at each location in ascending order

print(Student.objects.values('college__location').annotate(cnt=Count('id')).order_by('cnt'))

#get the location with max no of students
print(Student.objects.values('college__location').annotate(cnt=Count('id')).order_by('-cnt')[:1])  #use aggregate function
print(Student.objects.values('college__location').annotate(cnt=Count('id')).aggregate(ct2=Max('cnt'))) #gives 73 see sql functions
print(Student.objects.values('college__location').annotate(cnt=Count('id')))

#print student name, his total and college name

print(MockTest1.objects.values('total','student__name', 'student__college__name').order_by('-total'))
#since one-one it is possible
print(Student.objects.values('mocktest1__total','name','college__name'))

#print all students in a college

print(College.objects.values('student__name','name')) #left outer join

#print student details who have marks greater tha 30

print(Student.objects.values('mocktest1__total','name','college__name').filter(mocktest1__total__gt=30))

print(len(Student.objects.values('mocktest1__total','name','college__name').filter(mocktest1__total__gt=30)))

print(Student.objects.values('mocktest1__total','name','college__name').filter(mocktest1__total__gt=30).count())

#no of students with total greater than 30

print(MockTest1.objects.values('total').filter(total__gt=30).aggregate(cnt=Count('total')))
print(MockTest1.objects.values('total').filter(total__gt=30).annotate(cnt=Count('total')))
