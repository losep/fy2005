// shenji-steps.c
inherit SKILL;
void setup(){
	set("name","�������");
	set("type","step");
	set("difficulty",200);
	set("usage/dodge",1);
	set("usage/move",1);
	set("effective_level",150);
	set("skill_class","npc");
	set("dodge_msg", ({
		"$nһ�С�����ѿǡ����������飬����Ʈ����$N����ʽ��ա�\n",
		"ֻ��$n������������$N����ʽ���ϣ�һʽ���ٳղ�񲡹�����ɵض���һ�ԡ�\n",
		"$nʹ�������ܹ��ݡ���бб�شܿ���\n",
		"$n����һ�㣬һ�С����ɳ²֡��ڿն��𣬱��˿�ȥ��\n",
		"����$nʹһ�С����ݴ��͡�������Ʈ��������$N�Ĺ���ʧȥ��׼ͷ��\n",
		"$n����һ�С������ۻ𡹣�����Ʈ�ˣ�����������\n",
		"����$nһ�С�����ҽ���ʹ�������λζ����ó�������Ӱ���Լ�����Ʈ�����ɿ��⣡\n",
	}) );
}
