---
layout: template
title: Sponsors
---

<h2 class="sponsor-category">Platinum</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "platinum" %}
  <h3><a href="{{ d.link }}">{{ d.title }}</a></h3>
  <a href="{{ d.link }}"><img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="600px"></a>
  {% endif %}
{% endfor %}

<h2 class="sponsor-category">Gold</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "gold" %}
  <h3><a href="{{ d.link }}">{{ d.title }}</a></h3>
  <a href="{{ d.link }}"><img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="400px"></a>
  {% endif %}
{% endfor %}

<h2 class="sponsor-category">Silver</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "silver" %}
  <h3><a href="{{ d.link }}">{{ d.title }}</a></h3>
  <a href="{{ d.link }}"><img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="300px"></a>
  {% endif %}
{% endfor %}

<h2 class="sponsor-category">Bronze</h2>
{% for d in site.data.sponsors %}
  {% if d.category == "bronze" %}
  <h3><a href="{{ d.link }}">{{ d.title }}</a></h3>
  <a href="{{ d.link }}"><img src="{{ site.url }}/assets/img/stryke-force/sponsors/{{ d.file }}" width="200px"></a>
  {% endif %}
{% endfor %}
