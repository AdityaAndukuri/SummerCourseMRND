# Generated by Django 2.2.1 on 2019-06-17 07:13

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('cricbuzzapp', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='match',
            name='dl_applied',
            field=models.IntegerField(),
        ),
        migrations.AlterField(
            model_name='over',
            name='is_super_over',
            field=models.IntegerField(),
        ),
    ]